import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Random;
import java.util.Scanner;

public abstract class Vehicle {
    // Пункт 11: Static переменные и функции
    public static int totalVehiclesOnParking = 0; // сколько заехало на парковку
    public static double totalFleetMileage = 0.0; // общий пробег автопарка

    protected String brand;
    protected int year;
    protected double mileage;

    // Пункт 5: Конструктор без параметров
    public Vehicle() {
        this.brand = "Unknown";
        this.year = 2020;
        this.mileage = 0.0;
        totalVehiclesOnParking++;
        randomize(); // Пункт 7: Переопределить/вызвать Randomize в дефолтном конструкторе
    }

    // Пункт 5: Конструктор с параметрами
    public Vehicle(String brand, int year, double mileage) {
        this.brand = brand;
        this.year = year;
        this.mileage = mileage;
        totalVehiclesOnParking++;
        totalFleetMileage += mileage;
    }

    // Пункт 11: Статическая функция вывода статистики
    public static void printFleetStatistics() {
        System.out.println("\n[STATISTICS] Машин на парковке: " + totalVehiclesOnParking);
        System.out.println("[STATISTICS] Суммарный пробег автопарка: " + totalFleetMileage + " км.\n");
    }

    // Пункт 1: Абстрактная функция
    public abstract void startEngine();

    // Пункт 6: Обычная функция из класса родителя
    public void displayGeneralInfo() {
        System.out.println("Марка: " + brand + ", Год: " + year + ", Пробег: " + mileage + " км.");
    }

    // Пункт 7: Метод рандомизации полей
    public void randomize() {
        String[] brands = {"Toyota", "Ford", "BMW", "Mercedes", "Renault", "Hyundai"};
        Random rand = new Random();
        this.brand = brands[rand.nextInt(brands.length)];
        this.year = 2010 + rand.nextInt(15); // от 2010 до 2024
        this.mileage = Math.round(rand.nextDouble() * 150000.0 * 10.0) / 10.0;
        totalFleetMileage += this.mileage;
    }

    // Пункт 8: Функция ввода полей с клавиатуры
    public void inputFromKeyboard() {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Введите марку: ");
        this.brand = scanner.nextLine();
        System.out.print("Введите год выпуска: ");
        this.year = scanner.nextInt();
        System.out.print("Введите пробег: ");
        this.mileage = scanner.nextDouble();
        totalFleetMileage += this.mileage;
    }

    // Пункт 9: Функция записи в файл
    public void writeToFile(PrintWriter writer) {
        writer.println("Brand: " + brand + ", Year: " + year + ", Mileage: " + mileage);
    }
}