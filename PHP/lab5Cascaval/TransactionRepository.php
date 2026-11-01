<?php
declare(strict_types=1);

require_once 'Transaction.php';
require_once 'TransactionStorageInterface.php';

/**
 * Класс TransactionRepository
 * Отвечает за хранение коллекции транзакций.
 */

class TransactionRepository implements TransactionStorageInterface
{
    private array $transactions = [];

    public function addTransaction(Transaction $transaction): void
    {
        $this->transactions[] = $transaction;
    }

    public function removeTransactionById(int $id): void
    {
        $this->transactions = array_filter(
            $this->transactions,
            fn(Transaction $t) => $t->getId() !== $id
        );
        $this->transactions = array_values($this->transactions);
    }

    public function getAllTransactions(): array
    {
        return $this->transactions;
    }

    public function findById(int $id): ?Transaction
    {
        foreach ($this->transactions as $transaction) {
            if ($transaction->getId() === $id) {
                return $transaction;
            }
        }
        return null;
    }
}