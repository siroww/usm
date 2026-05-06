// ЗАДАНИЕ 5: Функция some(array, callback)
// Проверяет, есть ли хотя бы один элемент, удовлетворяющий условию

// Ищет условие
/**
 * @param {Array} array - Массив элементов
 * @param {Function} callback - Функция обратного вызова, принимающая (element, index, array)
 */
function some(array, callback) {
    for (let i = 0; i < array.length; i++) {
        if (callback(array[i], i, array)) { // элемент, индекс, массив
            return true;
        }
    }
    return false;
}

const numbers = [1, 3, 5, 6, 7];

console.log("--- (5.1) Есть четные числа? ---");
const hasEven = some(numbers, (num) => num % 2 === 0);
console.log("Array:", numbers);
console.log("Has even:", hasEven); // true

console.log("\n--- (5.2) Все четные? ---");
const oddNumbers = [1, 3, 5, 7, 9];
const hasEvenInOdd = some(oddNumbers, (num) => num % 2 === 0);
console.log("Array:", oddNumbers);
console.log("Has even:", hasEvenInOdd); // false

console.log("\n--- (5.3) Есть число > 100? ---");
const values = [10, 20, 50, 150];
const hasBig = some(values, (num) => num > 100);
console.log("Has > 100:", hasBig); // true

console.log("\n--- (5.4) Непустой массив ---");
const empty = [];
const anyElement = some(empty, (el) => el > 0);
console.log("Empty - has positive:", anyElement); // false
