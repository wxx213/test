package main;

import java.lang.reflect.Method;

public class AnnotationTest {
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
