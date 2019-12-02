package process;

import java.io.File;
import java.io.InputStream;
import java.util.ArrayList;
import java.util.List;

public class ProcessTest {


    public static void TestProcess(String[] args){
        List<String> command = new ArrayList<>();
        command.add("uname");
        command.add("-a");
        try {
            ProcessBuilder builder = new ProcessBuilder(command);
            builder.redirectErrorStream(true);
            Process process = builder.start();
            InputStream in=process.getInputStream();
            byte[] re=new byte[1024];
            while (in.read(re)!= -1) {
                System.out.println("==>"+new String(re));
            }
            in.close();
            if(process.isAlive()){
                process.waitFor();
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

}

