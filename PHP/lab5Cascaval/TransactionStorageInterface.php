<?php
declare(strict_types=1);

/**
 * Интерфейс TransactionStorageInterface
 * Определяет контракт для хранилища транзакций.
 */

interface TransactionStorageInterface
{
    public function addTransaction(Transaction $transaction): void;
    public function removeTransactionById(int $id): void;
    /** @return Transaction[] */
    public function getAllTransactions(): array;
    public function findById(int $id): ?Transaction;
}