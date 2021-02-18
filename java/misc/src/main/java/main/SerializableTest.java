package main;

import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.io.Serializable;
import com.caucho.hessian.io.*;
import java.io.ByteArrayOutputStream;
import java.io.ByteArrayInputStream;

public class SerializableTest {
    public static class user implements Serializable {
        private String name;

        public String getName() {
            return name;
        }

        public void setName(String name) {
            this.name = name;
        }

    }
    public static void javaSerializable(String[] args) {
        System.out.println("Starting test java serialization");
        try {
            FileOutputStream out =new FileOutputStream("test.txt");
            ObjectOutputStream obj_out = new ObjectOutputStream(out);
            user u = new user();
            u.setName("test");
            obj_out.writeObject(u);

            //利用readobject方法还原user对象
            FileInputStream in = new FileInputStream("test.txt");
            ObjectInputStream ins = new ObjectInputStream(in);
            user u1 = (user)ins.readObject();

            System.out.println("read user: " + u1 + "\nuser.name: " + u1.getName());
        } catch (FileNotFoundException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        } catch (IOException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        } catch (ClassNotFoundException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }
    }

    public static void hessianSerializable(String[] args) {
        System.out.println("Starting test hessian serialization");
        SerializerFactory serializerFactory = new SerializerFactory();
        ByteArrayOutputStream os = new ByteArrayOutputStream();
        AbstractHessianOutput out = new Hessian2Output(os);

        out.setSerializerFactory(serializerFactory);
        user u = new user();
        u.setName("test");
        try {
            out.writeObject(u);
            out.close();
        } catch (Exception e) {
            System.out.println("hessian serialize failed," + e);
        }
        byte[] bytes = os.toByteArray();
        System.out.println("serialized bytes: " + bytes);

        ByteArrayInputStream is = new ByteArrayInputStream(bytes);
        AbstractHessianInput in = new Hessian2Input(is);

        in.setSerializerFactory(serializerFactory);
        Object value = null;
        try {
            value = in.readObject();
            in.close();
        } catch (IOException e) {
            System.out.println("hessian deserialize failed," + e);
        }
        user u2 = (user)value;
        System.out.println("read user: " + u2 + "\nuser.name: " + u2.getName());
    }
    public static void testSerializable(String[] args) {
        javaSerializable(args);
        hessianSerializable(args);
    }
}
