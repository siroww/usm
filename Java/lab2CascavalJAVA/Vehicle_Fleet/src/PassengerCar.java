import java.io.PrintWriter;
import java.util.Scanner;

public class PassengerCar extends A_Vehicle {
    // Пункт 4: Уникальные поля
    private int passengerCapacity;
    private String transmissionType; // "Автомат" или "Механика"

    public PassengerCar() {
        super();
        this.passengerCapacity = 5;
        this.transmissionType = "Автомат";
    }

    public PassengerCar(String brand, int year, double mileage, int passengerCapacity, String transmissionType) {
        super(brand, year, mileage);
        this.passengerCapacity = passengerCapacity;
        this.transmissionType = transmissionType;
    }

    @Override
    public void startEngine() {
        System.out.println("Легковой автомобиль " + brand + " плавно заводит тихий двигатель.");
    }

    // Пункт 14: Уникальная функция
    public void activateCruiseControl() {
        System.out.println("-> " + brand + ": Круиз-контроль успешно активирован на скорости 110 км/ч.");
    }

    @Override
    public void randomize() {
        super.randomize();
        this.passengerCapacity = 2 + (int)(Math.random() * 5);
        this.transmissionType = Math.random() > 0.5 ? "Автомат" : "Механика";
    }

    @Override
    public void inputFromKeyboard() {
        super.inputFromKeyboard();
        Scanner scanner = new Scanner(System.in);
        System.out.print("Введите вместимость пассажиров: ");
        this.passengerCapacity = scanner.nextInt();
        scanner.nextLine(); // очистка буфера
        System.out.print("Введите тип коробки передач: ");
        this.transmissionType = scanner.nextLine();
    }

    @Override
    public void writeToFile(PrintWriter writer) {
        writer.print("[PassengerCar] ");
        super.writeToFile(writer);
        writer.println("   Capacity: " + passengerCapacity + ", Transmission: " + transmissionType);
    }
}




//        PassengerCar myCar = new PassengerCar();
//        vehicles.add(myCar);
//        myCar.inputFromKeyboard();