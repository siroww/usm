// ЗАДАНИЕ 3: Функция filter(array, callback)
// Фильтрует массив, оставляя только элементы, для которых callback вернул true

// Фильтрует массив
/**
 * @param {Array} array - Массив элементов
 * @param {Function} callback - Функция обратного вызова, принимающая (element, index, array)
 */
function filter(array, callback) {
    const result = [];
    for (let i = 0; i < array.length; i++) {
        if (callback(array[i], i, array)) { // элемент, индекс, массив
            result.push(array[i]);
        }
    }
    return result;
}

const numbers = [1, 2, 3, 4, 5, 6];

console.log("--- (3.1) Четные числа ---");
const evenNumbers = filter(numbers, (num) => num % 2 === 0);
console.log("Original:", numbers);
console.log("Even:", evenNumbers); // [2, 4, 6]

console.log("\n--- (3.2) Числа больше 10 ---");
const values = [5, 10, 15, 20, 8, 12];
const bigNumbers = filter(values, (num) => num > 10);
console.log("Numbers > 10:", bigNumbers); // [15, 20, 12]

console.log("\n--- (3.3) Длинные слова ---");
const words = ['apple', 'a', 'hello', 'hi', 'world'];
const longWords = filter(words, (word) => word.length > 2);
console.log("Words > 2 chars:", longWords); // ['apple', 'hello', 'world']
