// format.js — утилиты для форматирования чисел и валют

const CURRENCY_SYMBOLS = { usd: '$', eur: '€', rub: '₽' };

/**
 * Форматирует цену с символом валюты
 * @param {number|null} value - цена
 * @param {string} currency - код валюты
 * @returns {string}
 */
function formatPrice(value, currency = 'usd') {
  const sym = CURRENCY_SYMBOLS[currency] || '$';
  if (value === null || value === undefined) return '—';
  if (value >= 1000) {
    return sym + value.toLocaleString('en-US', { maximumFractionDigits: 2 });
  }
  if (value >= 1) {
    return sym + value.toFixed(4);
  }
  return sym + value.toFixed(8);
}

/**
 * Форматирует изменение цены за 24ч со знаком и процентом
 * @param {number|null} value
 * @returns {string}
 */
function formatChange(value) {
  if (value === null || value === undefined) return '—';
  const sign = value >= 0 ? '+' : '';
  return sign + value.toFixed(2) + '%';
}
