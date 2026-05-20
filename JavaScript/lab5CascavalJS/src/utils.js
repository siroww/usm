/**
 * Генерирует уникальный идентификатор на основе текущего времени.
 * @returns {string} Уникальный ID.
 */
export function generateId() {
  return Date.now().toString();
}

/**
 * Форматирует объект Date в строку вида "ДД.ММ.ГГГГ ЧЧ:ММ".
 * @param {Date} date - Дата для форматирования.
 * @returns {string} Отформатированная строка даты и времени.
 */
export function formatDate(date) {
  const pad = (n) => String(n).padStart(2, '0');
  return `${pad(date.getDate())}.${pad(date.getMonth() + 1)}.${date.getFullYear()} ${pad(date.getHours())}:${pad(date.getMinutes())}`;
}

/**
 * Возвращает первые 4 слова из строки.
 * @param {string} text - Исходный текст.
 * @returns {string} Краткое описание (до 4 слов).
 */
export function shortDescription(text) {
  return text.split(' ').slice(0, 4).join(' ');
}
