// Перебор массива
/**
 * @param {Array} array - Массив элементов
 * @param {Function} callback - Функция обратного вызова, принимающая (element, index, array)
 */
function forEach(array, callback) {
    for (let i = 0; i < array.length; i++) {
        callback(array[i], i, array); //элемент, индекс, массив
    }
}


/**
 * @param {Array} array - Массив элементов для печати
 */
function printArray(array) {
    forEach(array, (val, i) => {
        console.log(`Element ${i}: value ${val}`);
    });
}

/**
 * @param {Array} array - Массив элементов для печати
 */
function printArray1(array) {
    forEach(array, (val, i) => {
        console.log(`${i}: ${val}`);
    });
}


const myNumbers = [10, 20, 30];

console.log("--- (1.1 подробный) ---");
printArray(myNumbers);

console.log("\n--- (1.1 краткий) ---");
printArray1(myNumbers);

console.log("\n--- (1.2) ---");
forEach([5, 15], (el) => console.log("Число:", el));