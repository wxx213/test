package main;

import java.lang.reflect.Method;
import java.lang.annotation.*;

public class AnnotationTest {
    /**定义限额注解*/
    @Documented
    @Retention(RetentionPolicy.RUNTIME)
    @Target(ElementType.METHOD)
    public @interface MyTestAnnotation {
        double testValue() default 10000;
    }

    @MyTestAnnotation(testValue = 15000)
    public static void TestGetAnnotation(){
        processAnnotation();
    }

    private static void processAnnotation() {
        try {
            Method testGetAnnotation = AnnotationTest.class.getDeclaredMethod("TestGetAnnotation");
            boolean annotationPresent = testGetAnnotation.isAnnotationPresent(MyTestAnnotation.class);
            if (annotationPresent) {
                MyTestAnnotation annotation = testGetAnnotation.getAnnotation(MyTestAnnotation.class);
                double l = annotation.testValue();
				System.out.println("Annotation test value: " + l);
            }
        } catch (NoSuchMethodException e) {
            e.printStackTrace();
        }
    }
}
