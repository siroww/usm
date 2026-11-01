<?php
declare(strict_types=1);

require_once 'TransactionStorageInterface.php';

/**
 * Класс TransactionManager
 * Реализует бизнес-логику работы с транзакциями.
 */

class TransactionManager
{
    public function __construct(
        private TransactionStorageInterface $repository
    ) {
    }

    public function calculateTotalAmount(): float
    {
        $total = 0.0;
        foreach ($this->repository->getAllTransactions() as $transaction) {
            $total += $transaction->getAmount();
        }
        return $total;
    }

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

    public function sortTransactionsByDate(): array
    {
        $transactions = $this->repository->getAllTransactions();
        usort($transactions, fn(Transaction $a, Transaction $b) => strcmp($a->getDate(), $b->getDate()));
        return $transactions;
    }

    public function sortTransactionsByAmountDesc(): array
    {
        $transactions = $this->repository->getAllTransactions();
        usort($transactions, fn(Transaction $a, Transaction $b) => $b->getAmount() <=> $a->getAmount());
        return $transactions;
    }
}