<?php
declare(strict_types=1);

/**
 * Класс Transaction
 * Описывает одну банковскую транзакцию.
 */
class Transaction
{
    /**
     * Создаёт транзакцию с её основными данными.
     *
     * @param int $id Уникальный идентификатор транзакции.
     * @param string $date Дата транзакции в формате YYYY-MM-DD.
     * @param float $amount Сумма транзакции.
     * @param string $description Описание платежа.
     * @param string $merchant Получатель платежа.
     * @param string $category Категория получателя.
     */
    public function __construct(
        private int $id,
        private string $date,
        private float $amount,
        private string $description,
        private string $merchant,
        private string $category = 'Разное'
    ) {
    }

    /** Возвращает идентификатор транзакции. */
    public function getId(): int { return $this->id; }

    /** Возвращает дату транзакции. */
    public function getDate(): string { return $this->date; }

    /** Возвращает сумму транзакции. */
    public function getAmount(): float { return $this->amount; }

    /** Возвращает описание платежа. */
    public function getDescription(): string { return $this->description; }

    /** Возвращает получателя платежа. */
    public function getMerchant(): string { return $this->merchant; }

    /** Возвращает категорию получателя. */
    public function getCategory(): string { return $this->category; }

    /**
     * Вычисляет количество дней между датой транзакции и текущей датой.
     *
     * @return int Количество дней.
     */
    public function getDaysSinceTransaction(): int
    {
        $transactionDate = new DateTime($this->date);
        $currentDate = new DateTime();
        $interval = $transactionDate->diff($currentDate);

        return (int) $interval->format('%a');
    }
}