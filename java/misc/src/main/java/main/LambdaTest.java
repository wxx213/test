package main;


/**
 * LambdaDemo代码示例
 * <p>Title: LambdaDemo.java</p>
 * <p>Description: </p>
 * @author 荚小白
 * @date 2019年3月31日
 * @version 1.0
 * since jdk1.8
 */
public class LambdaTest {
    public static void TestLambda() {
        //原来的实现方式
        IDemoService demo1 = new IDemoService() {
            @Override
            public void print(String str1) {
                System.out.println(str1);
            }
        };
        demo1.print("old old old");

        //Lambda实现方式 （将new省去，方法定义省去，参数类型省去，只留下参数与方法的具体实现）
        IDemoService demo2 = (str2) -> System.out.println(str2);
        demo2.print("new one line");

        //具体实现有多行是需要用{}扩起来
        IDemoService demo3 = (str3) -> {
            str3 = str3 + " more line";
            System.out.println(str3);
        };
        demo3.print("new");
    }
}

/**
 * 接口必须只有一个方法
 * <p>Title: LambdaDemo.java</p>
 * <p>Description: </p>
 * @author 荚小白
 * @date 2019年3月31日
 * @version 1.0
 * since jdk1.8
 */
@FunctionalInterface
interface IDemoService {
    void print(String str);
}
