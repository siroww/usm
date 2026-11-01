import java.io.PrintWriter;
import java.util.Scanner;

public class Bus extends A_Vehicle implements I_CargoCarrier {
    // Пункт 4: Уникальные поля
    private int standingPlaces;
    private int routeNumber;

    public Bus() {
        super();
        this.standingPlaces = 30;
        this.routeNumber = 5;
    }

    public Bus(String brand, int year, double mileage, int standingPlaces, int routeNumber) {
        super(brand, year, mileage);
        this.standingPlaces = standingPlaces;
        this.routeNumber = routeNumber;
    }

    @Override
    public void startEngine() {
        System.out.println("Автобус маршрута №" + routeNumber + " (" + brand + ") заводит двигатель.");
    }

    // Пункт 14: Уникальная функция
    public void announceStop() {
        System.out.println("-> " + brand + " [Маршрут " + routeNumber + "]: Объявление следующей остановки в салоне.");
    }

    // Реализация интерфейса I_CargoCarrier (перевозка пассажиров как "живого груза")
    @Override
    public void loadCargo(double passengerCount) {
        System.out.println("-> Автобус " + brand + " принял на борту пассажиров: " + (int)passengerCount);
    }

    @Override
    public void unloadCargo() {
        System.out.println("-> Автобус " + brand + " высадил всех пассажиров на конечной остановке.");
    }

    @Override
    public void randomize() {
        super.randomize();
        this.standingPlaces = 15 + (int)(Math.random() * 35);
        this.routeNumber = 1 + (int)(Math.random() * 50);
    }

    @Override
    public void inputFromKeyboard() {
        super.inputFromKeyboard();
        Scanner scanner = new Scanner(System.in);
        System.out.print("Введите количество стоячих мест: ");
        this.standingPlaces = scanner.nextInt();
        System.out.print("Введите номер маршрута: ");
        this.routeNumber = scanner.nextInt();
    }

    @Override
    public void writeToFile(PrintWriter writer) {
        writer.print("[Bus] ");
        super.writeToFile(writer);
        writer.println("   Standing Places: " + standingPlaces + ", Route: " + routeNumber);
    }
}