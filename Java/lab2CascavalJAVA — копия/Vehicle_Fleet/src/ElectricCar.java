import java.io.PrintWriter;
import java.util.Scanner;

public class ElectricCar extends Vehicle implements Electric {
    // Пункт 4: Уникальные поля
    private double batteryCapacity; // кВт·ч
    private double autopilotVersion;

    public ElectricCar() {
        super();
        this.batteryCapacity = 75.0;
        this.autopilotVersion = 4.0;
    }

    public ElectricCar(String brand, int year, double mileage, double batteryCapacity, double autopilotVersion) {
        super(brand, year, mileage);
        this.batteryCapacity = batteryCapacity;
        this.autopilotVersion = autopilotVersion;
    }

    @Override
    public void startEngine() {
        System.out.println("Электромобиль " + brand + " активирован бесшумно (электромотор готов).");
    }

    // Пункт 14: Уникальная функция
    public void enableAutopilot() {
        System.out.println("-> " + brand + ": Автопилот v" + autopilotVersion + " включен. Управление передано ИИ.");
    }

    // Реализация интерфейса Electric
    @Override
    public void chargeBattery() {
        System.out.println("-> " + brand + ": Подключена быстрая зарядка. Батарея " + batteryCapacity + " кВт·ч заряжается.");
    }

    @Override
    public int getBatteryLevel() {
        return 85; // условный текущий заряд в %
    }

    @Override
    public void randomize() {
        super.randomize();
        this.batteryCapacity = 50.0 + Math.random() * 50.0;
        this.autopilotVersion = 2.0 + Math.floor(Math.random() * 4) + 0.5;
    }

    @Override
    public void inputFromKeyboard() {
        super.inputFromKeyboard();
        Scanner scanner = new Scanner(System.in);
        System.out.print("Введите емкость батареи (кВт·ч): ");
        this.batteryCapacity = scanner.nextDouble();
        System.out.print("Введите версию автопилота: ");
        this.autopilotVersion = scanner.nextDouble();
    }

    @Override
    public void writeToFile(PrintWriter writer) {
        writer.print("[ElectricCar] ");
        super.writeToFile(writer);
        writer.println("   Battery: " + batteryCapacity + " kWh, Autopilot: v" + autopilotVersion);
    }
}