// render.js — отрисовка карточек и модального окна

/**
 * Отрисовывает список карточек монет в grid
 * @param {Array} coins - массив монет
 * @param {string} currency - текущая валюта
 * @param {Function} onCardClick - коллбек при клике на карточку
 */
function renderCoins(coins, currency, onCardClick) {
  const grid = document.getElementById('grid');
  const emptyState = document.getElementById('emptyState');

  if (coins.length === 0) {
    grid.innerHTML = '';
    emptyState.classList.remove('hidden');
    return;
  }

  emptyState.classList.add('hidden');

  grid.innerHTML = coins.map((coin) => {
    const isUp = (coin.price_change_percentage_24h || 0) >= 0;
    const favActive = isFavorite(coin.id) ? 'active' : '';
    const favoritedClass = isFavorite(coin.id) ? 'favorited' : '';
    const changeClass = isUp ? 'up' : 'down';
    return `
      <div class="coin-card ${favoritedClass}"
           data-id="${coin.id}"
           role="button"
           tabindex="0">
        <div class="card-header">
          <span class="card-rank">#${coin.market_cap_rank}</span>
          <img class="card-img" src="${coin.image}" alt="${coin.name}" />
          <div class="card-name-wrap">
            <span class="card-name">${coin.name}</span>
            <span class="card-symbol">${coin.symbol.toUpperCase()}</span>
          </div>
          <button class="card-fav ${favActive}"
                  data-favid="${coin.id}"
                  title="Favorite">★</button>
        </div>
        <div class="card-price">${formatPrice(coin.current_price, currency)}</div>
        <div class="card-change ${changeClass}">${formatChange(coin.price_change_percentage_24h)}</div>
      </div>
    `;
  }).join('');

  // Навешиваем обработчики на каждую карточку
  coins.forEach(coin => {
    const card = grid.querySelector(`[data-id="${coin.id}"]`);
    if (!card) return;

    card.addEventListener('click', (e) => {
      if (e.target.closest('.card-fav')) return;
      onCardClick(coin);
    });

    card.addEventListener('keydown', (e) => {
      if (e.key === 'Enter' || e.key === ' ') {
        e.preventDefault();
        onCardClick(coin);
      }
    });

    const favBtn = card.querySelector('.card-fav');
    favBtn.addEventListener('click', (e) => {
      e.stopPropagation();
      const added = toggleFavorite(coin.id);
      favBtn.classList.toggle('active', added);
      card.classList.toggle('favorited', added);
    });
  });
}

/**
 * Открывает модальное окно с деталями монеты
 * @param {Object} coin - объект монеты
 * @param {string} currency - текущая валюта
 */
function openModal(coin, currency) {
  const modal = document.getElementById('modal');
  const isUp = (coin.price_change_percentage_24h || 0) >= 0;

  document.getElementById('modalImg').src = coin.image;
  document.getElementById('modalImg').alt = coin.name;
  document.getElementById('modalTitle').textContent = coin.name;
  document.getElementById('modalSymbol').textContent = coin.symbol.toUpperCase();
  document.getElementById('modalPrice').textContent = formatPrice(coin.current_price, currency);

  const changeEl = document.getElementById('modalChange');
  changeEl.textContent = formatChange(coin.price_change_percentage_24h);
  changeEl.style.color = isUp ? '#22c55e' : '#ef4444';

  const favBtn = document.getElementById('modalFavBtn');
  favBtn.textContent = isFavorite(coin.id) ? '★' : '☆';
  favBtn.onclick = () => {
    const added = toggleFavorite(coin.id);
    favBtn.textContent = added ? '★' : '☆';
  };

  modal.classList.remove('hidden');
  document.body.style.overflow = 'hidden';
}

/** Закрывает модальное окно */
function closeModal() {
  document.getElementById('modal').classList.add('hidden');
  document.body.style.overflow = '';
}
