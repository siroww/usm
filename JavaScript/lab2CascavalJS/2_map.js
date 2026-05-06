// ЗАДАНИЕ 2: Функция map(array, callback)
// Создает новый массив, содержащий результаты вызова callback для каждого элемента

// Создает массив
/**
 * @param {Array} array - Массив элементов
 * @param {Function} callback - Функция обратного вызова, принимающая (element, index, array)
 */
function map(array, callback) {
    const result = [];
    for (let i = 0; i < array.length; i++) {
        result.push(callback(array[i], i, array)); // элемент, индекс, массив
    }
    return result;
}

const numbers = [1, 2, 3];

console.log("--- (2.1) Возведение в квадрат ---");
const squared = map(numbers, (num) => num * num);
console.log("Original:", numbers);
console.log("Squared:", squared); // [1, 4, 9]

console.log("\n--- (2.2) Удвоение ---");
const doubled = map(numbers, (num) => num * 2);
console.log("Doubled:", doubled); // [2, 4, 6]