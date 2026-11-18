<?php
declare(strict_types=1);

require_once __DIR__ . '/TransactionStorageInterface.php';

/** Выполняет поиск, сортировку и вычисления для транзакций репозитория. */
class TransactionManager
{
    /**
     * Создаёт менеджер для переданного хранилища транзакций.
     *
     * @param TransactionStorageInterface $repository Хранилище транзакций.
     */
    public function __construct(
        private TransactionStorageInterface $repository
    ) {
    }

    /**
     * Считает общую сумму всех транзакций.
     *
     * @return float Общая сумма.
     */
    public function calculateTotalAmount(): float
    {
        $total = 0.0;
        foreach ($this->repository->getAllTransactions() as $transaction) {
            $total += $transaction->getAmount();
        }
        return $total;
    }

    /**
     * Считает сумму транзакций за указанный период включительно.
     *
     * @param string $startDate Начало периода в формате YYYY-MM-DD.
     * @param string $endDate Конец периода в формате YYYY-MM-DD.
     * @return float Сумма транзакций за период.
     */
    public function calculateTotalAmountByDateRange(string $startDate, string $endDate): float
    {
        $start = new DateTime($startDate);
        $end = new DateTime($endDate);
        $total = 0.0;

        foreach ($this->repository->getAllTransactions() as $transaction) {
            $tDate = new DateTime($transaction->getDate());
            if ($tDate >= $start && $tDate <= $end) {
                $total += $transaction->getAmount();
            }
        }
        return $total;
    }

    /**
     * Считает количество транзакций указанного получателя.
     *
     * @param string $merchant Название получателя.
     * @return int Количество найденных транзакций.
     */
    public function countTransactionsByMerchant(string $merchant): int
    {
        $count = 0;
        foreach ($this->repository->getAllTransactions() as $transaction) {
            if (strcasecmp($transaction->getMerchant(), $merchant) === 0) {
                $count++;
            }
        }
        return $count;
    }

    /**
     * Возвращает транзакции, отсортированные по дате от старых к новым.
     *
     * @return Transaction[] Отсортированный список транзакций.
     */
    public function sortTransactionsByDate(): array
    {
        $transactions = $this->repository->getAllTransactions();
        usort($transactions, static fn(Transaction $a, Transaction $b): int => strcmp($a->getDate(), $b->getDate()));
        return $transactions;
    }

    /**
     * Возвращает транзакции, отсортированные по сумме от большей к меньшей.
     *
     * @return Transaction[] Отсортированный список транзакций.
     */
    public function sortTransactionsByAmountDesc(?array $transactions = null): array
    {
        $transactions ??= $this->repository->getAllTransactions();
        usort($transactions, static fn(Transaction $a, Transaction $b): int => $b->getAmount() <=> $a->getAmount());
        return $transactions;
    }

    /**
     * Возвращает транзакции, отсортированные по сумме от меньшей к большей.
     *
     * @return Transaction[] Отсортированный список транзакций.
     */
    public function sortTransactionsByAmountAsc(?array $transactions = null): array
    {
        $transactions ??= $this->repository->getAllTransactions();
        usort($transactions, static fn(Transaction $a, Transaction $b): int => $a->getAmount() <=> $b->getAmount());
        return $transactions;
    }

    /**
     * Находит транзакции, совершённые в указанную дату.
     *
     * @param string $date Дата в формате YYYY-MM-DD.
     * @return Transaction[] Найденные транзакции.
     */
    public function findTransactionsByDate(string $date): array
    {
        return array_values(array_filter(
            $this->repository->getAllTransactions(),
            static fn(Transaction $transaction): bool => $transaction->getDate() === $date
        ));
    }
}