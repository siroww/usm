import { transactions, addTransaction, removeTransaction, calculateTotal } from './transactions.js';
import { renderRow, removeRow, updateTotal, showDetail, showError, clearError } from './ui.js';
import { generateId, formatDate } from './utils.js';

const form = document.getElementById('transaction-form');
const table = document.getElementById('transactions-table');

/**
 * Обработчик отправки формы — создаёт и добавляет транзакцию.
 * @param {Event} e - Событие submit.
 */
form.addEventListener('submit', (e) => {
  e.preventDefault();
  clearError();

  const amountVal = document.getElementById('amount').value.trim();
  const category = document.getElementById('category').value;
  const description = document.getElementById('description').value.trim();

  // Валидация
  if (!amountVal || isNaN(Number(amountVal))) {
    showError('Введите корректную сумму.');
    return;
  }
  if (!category) {
    showError('Выберите категорию.');
    return;
  }
  if (!description) {
    showError('Введите описание.');
    return;
  }

  const transaction = {
    id: generateId(),
    date: formatDate(new Date()),
    amount: Number(amountVal),
    category,
    description,
  };

  addTransaction(transaction);
  renderRow(transaction);
  updateTotal(calculateTotal());
  form.reset();
});

/**
 * Делегирование событий на таблицу:
 * - клик по кнопке "Удалить" → удаляет транзакцию
 * - клик по строке → показывает подробности
 * @param {MouseEvent} e - Событие клика.
 */
table.addEventListener('click', (e) => {
  const row = e.target.closest('tr[data-id]');
  if (!row) return;

  const id = row.dataset.id;

  // Удаление
  if (e.target.classList.contains('delete-btn')) {
    removeTransaction(id);
    removeRow(id);
    updateTotal(calculateTotal());
    return;
  }

  // Показ деталей
  const transaction = transactions.find((t) => t.id === id);
  if (transaction) {
    showDetail(transaction);
  }
});
