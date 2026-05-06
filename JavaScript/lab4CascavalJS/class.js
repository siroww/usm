/**
 * Класс Item описывает базовый предмет инвентаря.
 */
class Item {
  /**
   * @param {string} name Название предмета.
   * @param {number} weight Вес предмета.
   * @param {string} rarity Редкость предмета.
   */
  constructor(name, weight, rarity) {
    this.name = name;
    this.weight = weight;
    this.rarity = rarity;
  }

  /**
   * Возвращает строку с информацией о предмете.
   * @returns {string}
   */
  getInfo() {
    return `${this.name} (вес: ${this.weight} кг, редкость: ${this.rarity})`;
  }

  /**
   * Устанавливает новый вес предмета.
   * @param {number} newWeight Новый вес в килограммах.
   */
  setWeight(newWeight) {
    if (typeof newWeight !== "number" || newWeight < 0) {
      console.warn("Вес должен быть числом больше или равным нулю.");
      return;
    }
    this.weight = newWeight;
  }
}

/**
 * Класс Weapon расширяет Item и добавляет характеристики оружия.
 */
class Weapon extends Item {
  /**
   * @param {string} name Название оружия.
   * @param {number} weight Вес оружия.
   * @param {string} rarity Редкость оружия.
   * @param {number} damage Урон оружия.
   * @param {number} durability Прочность от 0 до 100.
   */
  constructor(name, weight, rarity, damage, durability) {
    super(name, weight, rarity);
    this.damage = damage;
    this.durability = Math.min(Math.max(durability, 0), 100);
  }

  /**
   * Использует оружие и уменьшает прочность на 10, если прочность положительная.
   */
  use() {
    if (this.durability <= 0) {
      console.log(`${this.name} больше не пригодно для использования.`);
      return;
    }
    this.durability = Math.max(this.durability - 10, 0);
  }

  /**
   * Восстанавливает прочность оружия до 100.
   */
  repair() {
    this.durability = 100;
  }

  /**
   * Возвращает строку с информацией об оружии, включая урон и прочность.
   * @returns {string}
   */
  getInfo() {
    return `${super.getInfo()} | урон: ${this.damage}, прочность: ${this.durability}`;
  }
}

console.log("--- Тестирование классов Item и Weapon ---");
const sword = new Item("Steel Sword", 3.5, "rare");
console.log(sword.getInfo());
sword.setWeight(4.0);
console.log("После изменения веса:", sword.getInfo());

const bow = new Weapon("Longbow", 2.0, "uncommon", 15, 100);
console.log(bow.getInfo());
bow.use();
console.log("Прочность после use():", bow.durability);
bow.repair();
console.log("Прочность после repair():", bow.durability);

const axe = new Weapon("Battle Axe", 5.4, "rare", 25, 80);
axe.use();
axe.use();
console.log("Axe after two uses:", axe.getInfo());





// Дополнительно: аналогичная функциональность реализована через функции-конструкторы.
// Этот блок не заменяет классы, а показывает другой способ создания тех же объектов.
/**
 * Функция-конструктор ItemConstructor для создания предметов.
 * @param {string} name
 * @param {number} weight
 * @param {string} rarity
 */
function ItemConstructor(name, weight, rarity) {
  this.name = name;
  this.weight = weight;
  this.rarity = rarity;
}

/**
 * Возвращает строку с информацией о предмете (функция-конструктор).
 * @returns {string}
 */
ItemConstructor.prototype.getInfo = function () {
  return `${this.name} (вес: ${this.weight} кг, редкость: ${this.rarity})`;
};

/**
 * Изменяет вес предмета (функция-конструктор).
 * @param {number} newWeight
 */
ItemConstructor.prototype.setWeight = function (newWeight) {
  if (typeof newWeight !== "number" || newWeight < 0) {
    console.warn("Вес должен быть числом больше или равным нулю.");
    return;
  }
  this.weight = newWeight;
};

/**
 * Функция-конструктор WeaponConstructor, унаследованная от ItemConstructor.
 * @param {string} name
 * @param {number} weight
 * @param {string} rarity
 * @param {number} damage
 * @param {number} durability
 */
function WeaponConstructor(name, weight, rarity, damage, durability) {
  ItemConstructor.call(this, name, weight, rarity);
  this.damage = damage;
  this.durability = Math.min(Math.max(durability, 0), 100);
}

WeaponConstructor.prototype = Object.create(ItemConstructor.prototype);
WeaponConstructor.prototype.constructor = WeaponConstructor;

WeaponConstructor.prototype.use = function () {
  if (this.durability <= 0) {
    console.log(`${this.name} больше не пригодно для использования.`);
    return;
  }
  this.durability = Math.max(this.durability - 10, 0);
};

WeaponConstructor.prototype.repair = function () {
  this.durability = 100;
};

WeaponConstructor.prototype.getInfo = function () {
  return `${this.name} (вес: ${this.weight} кг, редкость: ${this.rarity}) | урон: ${this.damage}, прочность: ${this.durability}`;
};

console.log("--- Тестирование дополнительной реализации через функции-конструкторы ---");
const dagger = new ItemConstructor("Dagger", 1.2, "common");
console.log(dagger.getInfo());
dagger.setWeight(1.3);
console.log("После изменения веса:", dagger.getInfo());

const spear = new WeaponConstructor("Spear", 3.1, "uncommon", 18, 90);
console.log(spear.getInfo());
spear.use();
console.log("Прочность копья после use():", spear.durability);
spear.repair();
console.log("Прочность копья после repair():", spear.durability);

// Пример использования опциональной цепочки, чтобы избежать ошибки в случае отсутствующего объекта.
console.log("Опциональная цепочка для spear:", spear?.damage);
console.log("Опциональная цепочка для несуществующего объекта:", undefined?.name);
