import { shortDescription } from './utils.js';

/**
 * Добавляет строку транзакции в таблицу.
 * @param {{ id: string, date: string, amount: number, category: string, description: string }} transaction
 */
export function renderRow(transaction) {
  const tbody = document.getElementById('table-body');
  const tr = document.createElement('tr');
  tr.dataset.id = transaction.id;
  tr.classList.add(transaction.amount >= 0 ? 'income' : 'expense');

  tr.innerHTML = `
    <td>${transaction.date}</td>
    <td>${transaction.category}</td>
    <td>${shortDescription(transaction.description)}</td>
    <td><button class="delete-btn">Удалить</button></td>
  `;

  tbody.appendChild(tr);
}

/**
 * Удаляет строку таблицы по ID транзакции.
 * @param {string} id - Идентификатор транзакции.
 */
export function removeRow(id) {
  const row = document.querySelector(`tr[data-id="${id}"]`);
  if (row) row.remove();
}

/**
 * Обновляет отображение общего баланса.
 * @param {number} total - Новое значение баланса.
 */
export function updateTotal(total) {
  document.getElementById('total').textContent = total;
}

/**
 * Отображает полное описание транзакции в блоке деталей.
 * @param {{ date: string, amount: number, category: string, description: string }} transaction
 */
export function showDetail(transaction) {
  const detail = document.getElementById('detail-text');
  detail.textContent = `[${transaction.date}] ${transaction.category} | ${transaction.amount} руб. | ${transaction.description}`;
}

/**
 * Выводит сообщение об ошибке формы.
 * @param {string} message - Текст ошибки.
 */
export function showError(message) {
  document.getElementById('form-error').textContent = message;
}

/**
 * Очищает сообщение об ошибке формы.
 */
export function clearError() {
  document.getElementById('form-error').textContent = '';
}
