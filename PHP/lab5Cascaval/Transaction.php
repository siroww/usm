<?php
declare(strict_types=1);

/**
 * Класс Transaction
 * Описывает одну банковскую транзакцию.
 */
class Transaction
{
    public function __construct(
        private int $id,
        private string $date,
        private float $amount,
        private string $description,
        private string $merchant,
        private string $category = 'Разное'
    ) {
    }

    public function getId(): int { return $this->id; }
    public function getDate(): string { return $this->date; }
    public function getAmount(): float { return $this->amount; }
    public function getDescription(): string { return $this->description; }
    public function getMerchant(): string { return $this->merchant; }
    public function getCategory(): string { return $this->category; }

    public function getDaysSinceTransaction(): int
    {
        $transactionDate = new DateTime($this->date);
        $currentDate = new DateTime();
        $interval = $transactionDate->diff($currentDate);
        return (int) $interval->format('%a');
    }
}