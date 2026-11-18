<?php
declare(strict_types=1);

/**
 * Интерфейс TransactionStorageInterface
 * Определяет контракт для хранилища транзакций.
 */

interface TransactionStorageInterface
{
    /**
     * Добавляет транзакцию в хранилище.
     *
     * @param Transaction $transaction Транзакция для добавления.
     */
    public function addTransaction(Transaction $transaction): void;

    /**
     * Удаляет транзакцию по ID.
     *
     * @param int $id Идентификатор транзакции.
     */
    public function removeTransactionById(int $id): void;

    /**
     * Возвращает все транзакции.
     *
     * @return Transaction[] Список транзакций.
     */
    public function getAllTransactions(): array;

    /**
     * Ищет транзакцию по ID.
     *
     * @param int $id Идентификатор транзакции.
     * @return Transaction|null Найденная транзакция или null.
     */
    public function findById(int $id): ?Transaction;
}