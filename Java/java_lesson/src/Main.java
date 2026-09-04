import java.util.Arrays;

// Класс Student без модификатора public, чтобы его можно было держать в одном файле
class Student {
    String nickName;
    float laziness;     // 0..1 - лень
    byte IQ;           // 80…127
    int exams;
    int[] marks;       // динамический массив
    static int nrStudent;

    // 1. Конструктор по умолчанию
    public Student() {
        nickName = "oleg";
        laziness = (float) 0.5;    // 0.5f
        IQ = (byte) 127;
        exams = 6;
        marks = new int[exams];
        for (int i = 0; i < exams; i++) {
            marks[i] = 7;
        }
        nrStudent++;
    }

    // 2. Конструктор с параметрами
    public Student(float laziness, byte IQ) {
        nickName = "artem";
        this.laziness = laziness;
        this.IQ = IQ;
        exams = 18;
        marks = new int[exams];
        for (int i = 0; i < exams; i++) {
            marks[i] = 8;
        }
        nrStudent++;
    }

    // 3. Конструктор копирования
    public Student(Student prototype) {
        nickName = prototype.nickName;
        laziness = prototype.laziness;
        IQ = prototype.IQ;
        exams = prototype.exams;
        marks = new int[exams];
        for (int i = 0; i < exams; i++) {
            marks[i] = prototype.marks[i];
        }
        nrStudent++;
    }

    // Метод вывода информации
    public void printInfo() {
        System.out.println("Student’s nick: " + nickName);
        System.out.println("Laziness: " + laziness);
        System.out.println("IQ: " + IQ);
        System.out.println("Exams: " + exams);
        System.out.print("Marks: ");
        for (int i = 0; i < exams; i++) {
            System.out.print(marks[i] + " ");
        }
        System.out.println();
    }

    public static void main( String[] sui ){
        Student Artemii;
        Artemii = new Student();

        Student Seva = new Student(0.67f, (byte) 110);

        Student Klon = new Student(Artemii);

        Artemii.printInfo();
        Klon.printInfo();

        Student I2502[] = new Student[18];
        for(int i=0;i<I2502.length;i+=3){
            I2502[i] = new Student();
            I2502[i+1] = new Student((float)(i+0.01), (byte)(100+i));
            I2502[i+2] = new Student(I2502[i+1]);
        }

        for (int i=0; i<I2502.length; i++) {
            I2502[i].printInfo();
        }

        // поиск самого маленького айкю у студента
        Student minIQ = I2502[0];
        for (int i=1; i<I2502.length; i++) {
            if (I2502[i].IQ < minIQ.IQ){minIQ = I2502[i];};
            System.out.println("sami min IQ");
            minIQ.printInfo();
        }
        Student maxLeziness = I2502[0];
        for (int i=1; i<I2502.length; i++) {
            if (I2502[i].laziness > minIQ.laziness){maxLeziness = I2502[i];};
            System.out.println("sami max laziness:");
            maxLeziness.printInfo();
        }
        System.out.println("Students in Universitate:" + nrStudent);
    }


}

