package main;

import java.lang.annotation.*;

/**定义限额注解*/
@Documented
@Retention(RetentionPolicy.RUNTIME)
@Target(ElementType.METHOD)
public @interface MyTestAnnotation {
    double testValue() default 10000;
}
