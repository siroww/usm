<?php
declare(strict_types=1);

require_once __DIR__ . '/Transaction.php';
require_once __DIR__ . '/TransactionStorageInterface.php';

/**
 * Класс TransactionRepository
 * Отвечает за хранение коллекции транзакций.
 */

class TransactionRepository implements TransactionStorageInterface
{
    /** @var Transaction[] */
    private array $transactions = [];

    /**
     * Загружает коллекцию из текстового файла, если путь к файлу указан.
     *
     * @param string|null $filename Путь к CSV-файлу для хранения транзакций.
     */
    public function __construct(private ?string $filename = null)
    {
        if ($this->filename !== null && is_file($this->filename)) {
            $this->transactions = $this->loadFromFile();
        }
    }

    /**
     * Добавляет транзакцию и сохраняет коллекцию в файл.
     *
     * @param Transaction $transaction Транзакция для добавления.
     */
    public function addTransaction(Transaction $transaction): void
    {
        if ($this->findById($transaction->getId()) !== null) {
            throw new InvalidArgumentException('Транзакция с таким ID уже существует.');
        }

        $this->transactions[] = $transaction;
        $this->saveToFile();
    }

    /**
     * Удаляет транзакцию по ID и сохраняет обновлённую коллекцию.
     *
     * @param int $id Идентификатор транзакции.
     */
    public function removeTransactionById(int $id): void
    {
        $this->transactions = array_filter(
            $this->transactions,
            static fn(Transaction $transaction): bool => $transaction->getId() !== $id
        );
        $this->transactions = array_values($this->transactions);
        $this->saveToFile();
    }

    /**
     * Возвращает все транзакции.
     *
     * @return Transaction[] Список транзакций.
     */
    public function getAllTransactions(): array
    {
        return $this->transactions;
    }

    /**
     * Находит транзакцию по ID.
     *
     * @param int $id Идентификатор транзакции.
     * @return Transaction|null Найденная транзакция или null.
     */
    public function findById(int $id): ?Transaction
    {
        foreach ($this->transactions as $transaction) {
            if ($transaction->getId() === $id) {
                return $transaction;
            }
        }
        return null;
    }

    /**
     * Загружает транзакции из CSV-файла.
     *
     * @return Transaction[] Загруженные транзакции.
     */
    private function loadFromFile(): array
    {
        $file = fopen($this->filename, 'r');
        if ($file === false) {
            throw new RuntimeException('Не удалось открыть файл транзакций для чтения.');
        }

        if (!flock($file, LOCK_SH)) {
            fclose($file);
            throw new RuntimeException('Не удалось заблокировать файл транзакций для чтения.');
        }

        $transactions = [];
        while (($row = fgetcsv($file, null, ';', '"', '\\')) !== false) {
            if (count($row) !== 6 || !is_numeric($row[0]) || !is_numeric($row[2])) {
                flock($file, LOCK_UN);
                fclose($file);
                throw new RuntimeException('Файл транзакций содержит строку в неверном формате.');
            }

            $transactions[] = new Transaction(
                (int) $row[0],
                $row[1],
                (float) $row[2],
                $row[3],
                $row[4],
                $row[5]
            );
        }

        flock($file, LOCK_UN);
        fclose($file);

        return $transactions;
    }

    /**
     * Перезаписывает CSV-файл текущим списком транзакций.
     */
    private function saveToFile(): void
    {
        if ($this->filename === null) {
            return;
        }

        $file = fopen($this->filename, 'c+');
        if ($file === false) {
            throw new RuntimeException('Не удалось открыть файл транзакций для записи.');
        }

        if (!flock($file, LOCK_EX)) {
            fclose($file);
            throw new RuntimeException('Не удалось заблокировать файл транзакций для записи.');
        }

        if (!ftruncate($file, 0) || rewind($file) === false) {
            flock($file, LOCK_UN);
            fclose($file);
            throw new RuntimeException('Не удалось подготовить файл транзакций к записи.');
        }

        foreach ($this->transactions as $transaction) {
            if (fputcsv($file, [
                $transaction->getId(),
                $transaction->getDate(),
                $transaction->getAmount(),
                $transaction->getDescription(),
                $transaction->getMerchant(),
                $transaction->getCategory(),
            ], ';', '"', '\\') === false) {
                flock($file, LOCK_UN);
                fclose($file);
                throw new RuntimeException('Не удалось сохранить транзакцию в файл.');
            }
        }

        if (!fflush($file)) {
            flock($file, LOCK_UN);
            fclose($file);
            throw new RuntimeException('Не удалось завершить запись файла транзакций.');
        }
        flock($file, LOCK_UN);
        fclose($file);
    }
}