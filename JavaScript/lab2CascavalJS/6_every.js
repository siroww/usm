// ЗАДАНИЕ 6: Функция every(array, callback)
// Проверяет, удовлетворяют ли ВСЕ элементы условию
// Проверяет все

/**
 * @param {Array} array - Массив элементов
 * @param {Function} callback - Функция обратного вызова, принимающая (element, index, array)
 */
function every(array, callback) {
    for (let i = 0; i < array.length; i++) {
        if (!callback(array[i], i, array)) {
            return false;
        }
    }
    return true;
}

const evenNumbers = [2, 4, 6, 8];

console.log("--- (6.1) Все ли четные? ---");
const allEven = every(evenNumbers, (num) => num % 2 === 0);
console.log("All even:", allEven);

console.log("\n--- (6.2) Все четные (с нечетным) ---");
const mixed = [2, 4, 6, 7];
const allEvenMixed = every(mixed, (num) => num % 2 === 0);
console.log("Array:", mixed);
console.log("All even:", allEvenMixed); // false

console.log("\n--- (6.3) Все > 0? ---");
const positive = [1, 5, 10, 100];
const allPositive = every(positive, (num) => num > 0);
console.log("Array:", positive);
console.log("All positive:", allPositive); // true

console.log("\n--- (6.4) Все непустые строки? ---");
const words = ['hello', 'world', 'test'];
const allNonEmpty = every(words, (word) => word.length > 0);
console.log("Array:", words);
console.log("All non-empty:", allNonEmpty); // true

console.log("\n--- (6.5) Пустой массив ---");
const empty = [];
const allInEmpty = every(empty, (el) => el > 0);
console.log("Empty array - all satisfy:", allInEmpty); // true
