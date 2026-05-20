/**
 * Массив всех транзакций.
 * Каждый элемент: { id, date, amount, category, description }
 * @type {Array<Object>}
 */
export const transactions = [];

/**
 * Добавляет транзакцию в массив.
 * @param {{ id: string, date: string, amount: number, category: string, description: string }} transaction
 */
export function addTransaction(transaction) {
  transactions.push(transaction);
}

/**
 * Удаляет транзакцию из массива по ID.
 * @param {string} id - Идентификатор удаляемой транзакции.
 */
export function removeTransaction(id) {
  const index = transactions.findIndex((t) => t.id === id);
  if (index !== -1) {
    transactions.splice(index, 1);
  }
}

/**
 * Вычисляет общую сумму всех транзакций.
 * @returns {number} Итоговая сумма.
 */
export function calculateTotal() {
  return transactions.reduce((sum, t) => sum + t.amount, 0);
}
