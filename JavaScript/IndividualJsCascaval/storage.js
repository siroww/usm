// storage.js — работа с localStorage для избранных монет

const FAVORITES_KEY = 'cryptoboard_favorites';

/**
 * Возвращает массив id избранных монет из localStorage
 * @returns {string[]}
 */
function getFavorites() {
  try {
    return JSON.parse(localStorage.getItem(FAVORITES_KEY)) || [];
  } catch {
    return [];
  }
}

/**
 * Проверяет, является ли монета избранной
 * @param {string} coinId
 * @returns {boolean}
 */
function isFavorite(coinId) {
  return getFavorites().includes(coinId);
}

/**
 * Добавляет или удаляет монету из избранного
 * @param {string} coinId
 * @returns {boolean} true — если добавлена, false — если удалена
 */
function toggleFavorite(coinId) {
  const favs = getFavorites();
  const index = favs.indexOf(coinId);
  if (index === -1) {
    favs.push(coinId);
    localStorage.setItem(FAVORITES_KEY, JSON.stringify(favs));
    return true;
  } else {
    favs.splice(index, 1);
    localStorage.setItem(FAVORITES_KEY, JSON.stringify(favs));
    return false;
  }
}
