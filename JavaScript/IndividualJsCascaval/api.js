// api.js — работа с CoinGecko API

const BASE_URL = 'https://api.coingecko.com/api/v3';

/**
 * Загружает список монет по рыночной капитализации
 * @param {string} currency - валюта (usd, eur, rub)
 * @param {number} perPage - количество монет
 * @returns {Promise<Array>} массив монет
 */
async function fetchCoins(currency = 'usd', perPage = 10) {
  const url = BASE_URL
    + '/coins/markets?vs_currency=' + currency
    + '&order=market_cap_desc&per_page=' + perPage
    + '&page=1&price_change_percentage=24h';
  const res = await fetch(url);
  if (!res.ok) throw new Error('API error: ' + res.status);
  return res.json();
}
