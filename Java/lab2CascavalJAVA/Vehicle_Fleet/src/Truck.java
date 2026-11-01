import java.io.PrintWriter;
import java.util.Scanner;

public class Truck extends A_Vehicle implements I_CargoCarrier {
    // Пункт 4: Уникальные поля
    private double maxLoadCapacity; // в тоннах
    private int axleCount;          // количество осей

    public Truck() {
        super();
        this.maxLoadCapacity = 20.0;
        this.axleCount = 4;
    }

    public Truck(String brand, int year, double mileage, double maxLoadCapacity, int axleCount) {
        super(brand, year, mileage);
        this.maxLoadCapacity = maxLoadCapacity;
        this.axleCount = axleCount;
    }

    @Override
    public void startEngine() {
        System.out.println("Грузовик " + brand + " запускает мощный дизельный двигатель с гудком.");
    }

    // Пункт 14: Уникальная функция
    public void dumpCargo() {
        System.out.println("-> " + brand + ": Кузов поднят, груз успешно выгружен.");
    }

    // Реализация интерфейса I_CargoCarrier
    @Override
    public void loadCargo(double weight) {
        System.out.println("-> " + brand + ": Загружено " + weight + " тонн (Максимум: " + maxLoadCapacity + " т).");
    }

    @Override
    public void unloadCargo() {
        System.out.println("-> " + brand + ": Произведена полная разгрузка кузова.");
    }

    @Override
    public void randomize() {
        super.randomize();
        this.maxLoadCapacity = 10.0 + Math.random() * 30.0;
        this.axleCount = 2 + (int)(Math.random() * 4);
    }

    @Override
    public void inputFromKeyboard() {
        super.inputFromKeyboard();
        Scanner scanner = new Scanner(System.in);
        System.out.print("Введите макс. грузоподъемность (тонн): ");
        this.maxLoadCapacity = scanner.nextDouble();
        System.out.print("Введите количество осей: ");
        this.axleCount = scanner.nextInt();
    }

    @Override
    public void writeToFile(PrintWriter writer) {
        writer.print("[Truck] ");
        super.writeToFile(writer);
        writer.println("   Max Load: " + maxLoadCapacity + "t, Axles: " + axleCount);
    }
}