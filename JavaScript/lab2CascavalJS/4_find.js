// ЗАДАНИЕ 4: Функция find(array, callback)
// Возвращает первый элемент, удовлетворяющий условию (или undefined)

// Находит элемент
/**
 * @param {Array} array - Массив элементов
 * @param {Function} callback - Функция обратного вызова, принимающая (element, index, array)
 */
function find(array, callback) {
    for (let i = 0; i < array.length; i++) {
        if (callback(array[i], i, array)) { // элемент, индекс, массив
            return array[i];
        }
    }
    return undefined;
}

const numbers = [1, 3, 5, 6, 8];

console.log("--- (4.1) Первое четное число ---");
const firstEven = find(numbers, (num) => num % 2 === 0);
console.log("Array:", numbers);
console.log("First even:", firstEven); // 6

console.log("\n--- (4.2) Число больше 10 ---");
const values = [5, 8, 12, 3, 15];
const firstBig = find(values, (num) => num > 10);
console.log("First > 10:", firstBig); // 12

console.log("\n--- (4.3) Поиск объекта ---");
const users = [
    { id: 1, name: 'Alice' },
    { id: 2, name: 'Bob' },
    { id: 3, name: 'Charlie' }
];
const bobUser = find(users, (user) => user.name === 'Bob');
console.log("Found:", bobUser); // { id: 2, name: 'Bob' }
