// app.js — главный модуль, состояние и логика приложения

// Глобальное состояние приложения
let coins = [];
let filtered = [];
let currency = 'usd';
let search = '';
let sort = 'market_cap_desc';
let showFavOnly = false;

/**
 * Загружает данные с API и обновляет список монет
 */
async function loadData() {
  try {
    coins = await fetchCoins(currency, 10);
    applyFilters();
    document.getElementById('errorBanner').classList.add('hidden');
  } catch (err) {
    console.error('Ошибка загрузки:', err);
    document.getElementById('errorBanner').classList.remove('hidden');
  }
}

/**
 * Применяет фильтры, поиск и сортировку к списку монет
 */
function applyFilters() {
  let result = [...coins];

  // Фильтр по избранным
  if (showFavOnly) {
    const favs = getFavorites();
    result = result.filter(c => favs.includes(c.id));
  }

  // Поиск по названию и символу
  if (search) {
    const q = search.toLowerCase();
    result = result.filter(c =>
      c.name.toLowerCase().includes(q) || c.symbol.toLowerCase().includes(q)
    );
  }

  // Сортировка по цене
  if (sort === 'price_desc') {
    result.sort((a, b) => b.current_price - a.current_price);
  }

  filtered = result;
  renderCoins(filtered, currency, handleCardClick);
}

/**
 * Обработчик клика по карточке монеты
 * @param {Object} coin
 */
function handleCardClick(coin) {
  openModal(coin, currency);
}

/**
 * Навешивает все обработчики событий интерфейса
 */
function setupEventListeners() {
  // Поиск
  document.getElementById('searchInput').addEventListener('input', (e) => {
    search = e.target.value.trim();
    applyFilters();
  });

  // Смена валюты — перезагружает данные
  document.getElementById('currencySelect').addEventListener('change', (e) => {
    currency = e.target.value;
    loadData();
  });

  // Сортировка
  document.getElementById('sortSelect').addEventListener('change', (e) => {
    sort = e.target.value;
    applyFilters();
  });

  // Фильтр избранных
  document.getElementById('favBtn').addEventListener('click', () => {
    showFavOnly = !showFavOnly;
    document.getElementById('favBtn').classList.toggle('active', showFavOnly);
    applyFilters();
  });

  // Обновить данные
  document.getElementById('refreshBtn').addEventListener('click', loadData);

  // Закрытие модального окна
  document.getElementById('modalClose').addEventListener('click', closeModal);
  document.getElementById('modal').addEventListener('click', (e) => {
    if (e.target === e.currentTarget) closeModal();
  });
  document.addEventListener('keydown', (e) => {
    if (e.key === 'Escape') closeModal();
  });
}
// Сохраняет монеты в localStorage
function saveToCache(data) {
  localStorage.setItem('coins_cache', JSON.stringify(data));
  localStorage.setItem('coins_cache_time', Date.now());
}

// Читает монеты из localStorage
function loadFromCache() {
  const data = localStorage.getItem('coins_cache');
  return data ? JSON.parse(data) : null;
}

// Обновлённый loadData
async function loadData() {
  try {
    coins = await fetchCoins(currency, 10);
    saveToCache(coins);
    document.getElementById('errorBanner').classList.add('hidden');
  } catch (err) {
    console.error('Ошибка загрузки:', err);

    const cached = loadFromCache();
    if (cached) {
      coins = cached;
      const time = new Date(+localStorage.getItem('coins_cache_time'));
      const timeStr = time.toLocaleTimeString();
      document.getElementById('errorBanner').textContent =
        `Нет соединения. Показаны данные от ${timeStr}`;
      document.getElementById('errorBanner').classList.remove('hidden');
    } else {
      document.getElementById('errorBanner').classList.remove('hidden');
    }
  } finally {
    applyFilters();
  }
}

// Глобальная функция для кнопки "Повторить" в error banner
window.retry = loadData;

// Инициализация приложения
loadData();
setupEventListeners();
