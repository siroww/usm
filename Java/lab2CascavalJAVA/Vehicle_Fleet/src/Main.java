import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;

public class Main {
    public static void main(String[] args) {
        // Демонстрация final класса (Пункт 10)
        FleetConfig.printFleetRules();
        System.out.println("Компания: " + FleetConfig.COMPANY_NAME + "\n");

        // Пункт 13: Создать вектора объектов с типами: базовый класс && интерфейс
        ArrayList<A_Vehicle> vehicles = new ArrayList<>();
        ArrayList<I_Electric> electricVehicles = new ArrayList<>();

        // Заполняем вектор объектов разных наследников (вызываются конструкторы без параметров с рандомом)
        vehicles.add(new PassengerCar("Toyota Camry", 2022, 45000.0, 5, "Автомат"));
        vehicles.add(new Truck("Volvo FH", 2020, 180000.0, 25.0, 4));
        vehicles.add(new ElectricCar("Tesla Model S", 2023, 15000.0, 100.0, 4.5));
        vehicles.add(new Bus("Mercedes-Benz Conecto", 2021, 95000.0, 40, 23));

        // Добавляем еще один объект через дефолтный конструктор (проверка рандомизатора)
        vehicles.add(new ElectricCar());

        A_Vehicle mySuuperCar = new Truck();
        ((Truck)mySuuperCar).dumpCargo();


        // Заполняем вектор интерфейса I_Electric
        for (A_Vehicle v : vehicles) {
            if (v instanceof I_Electric) {
                electricVehicles.add((I_Electric) v);
            }
        }

        // Вывод статистики парковки (Пункт 11)
        A_Vehicle.printFleetStatistics();

        // Пункт 14: В функции main для созданных объектов вызвать уникальные функции, полиморфизм
        System.out.println("=== ДЕМОНСТРАЦИЯ ПОЛИМОРФИЗМА И УНИКАЛЬНЫХ ФУНКЦИЙ ===");
        for (A_Vehicle v : vehicles) {
            v.displayGeneralInfo(); // функция родителя (Пункт 6)
            v.startEngine();        // полиморфный вызов абстрактной функции

            // Пункт 12 и 14: Использовать instanceof и преобразование типов для вызова уникальных методов
            if (v instanceof PassengerCar) {
                ((PassengerCar) v).activateCruiseControl();
            } else if (v instanceof Truck) {
                Truck truck = (Truck) v; // преобразование типа
                truck.loadCargo(18.5);
                truck.dumpCargo();
            } else if (v instanceof ElectricCar) {
                ElectricCar ec = (ElectricCar) v;
                ec.enableAutopilot();
                ec.chargeBattery();
            } else if (v instanceof Bus) {
                Bus bus = (Bus) v;
                bus.loadCargo(45);
                bus.announceStop();
            }
            System.out.println("--------------------------------------------------");
        }

        // Демонстрация работы с интерфейсом I_Electric
        System.out.println("\n=== ОБЪЕКТЫ ИНТЕРФЕЙСА ELECTRIC ===");
        for (I_Electric el : electricVehicles) {
            el.chargeBattery();
            System.out.println("Текущий заряд батареи: " + el.getBatteryLevel() + "%");
        }

        // Пункт 9: Запись объектов в файл
        try (PrintWriter writer = new PrintWriter(new FileWriter("fleet_report.txt"))) {
            writer.println("=== ОТЧЕТ АВТОПАРКА ===");
            for (A_Vehicle v : vehicles) {
                v.writeToFile(writer); // полиморфный вызов записи в файл
            }
            System.out.println("\n[INFO] Данные успешно записаны в файл 'fleet_report.txt'.");
        } catch (IOException e) {
            System.out.println("[ERROR] Ошибка записи в файл: " + e.getMessage());
        }
    }
}