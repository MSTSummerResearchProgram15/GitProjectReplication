import java.io.*;
import java.util.*;

public class FileIO {

public static void main(String args[]) {        
    try {
        File input = new File("Data_10.txt");
        File output = new File("Data_20.txt");
        Scanner sc = new Scanner(input);
        PrintWriter printer = new PrintWriter(output);
        while(sc.hasNextLine()) {
            String s = sc.nextLine();
            printer.write(s);
            printer.write(s);
        }
    }
    catch(FileNotFoundException e) {
        System.err.println("File not found. Please scan in new file.");
    }
}
}
