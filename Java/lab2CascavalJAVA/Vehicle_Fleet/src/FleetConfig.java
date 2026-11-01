public final class FleetConfig {
    public static final String COMPANY_NAME = "CityFleet Management"; // final переменная

    public static final void printFleetRules() { // final функция
        System.out.println("--- Правила автопарка (" + COMPANY_NAME + ") ---");
        System.out.println("1. Все транспортные средства проходят ежедневный техосмотр.");
        System.out.println("2. Запрещена эксплуатация с неисправной тормозной системой.");
    }
}