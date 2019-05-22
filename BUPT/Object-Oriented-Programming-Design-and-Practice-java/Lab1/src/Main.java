import A.A;
import B.B;
import source.Base;

public class Main {

    public static void main(String[] args) {
        A a = new A((byte) 1, 2, "a");
        B b = new B((byte) 11, 22.2, 'b');

        System.out.println("a.setByte((byte) 9, b);");
        a.setByte((byte) 9, b);
        System.out.println(a.getString() + ":"+a.getByte() + ","+ a.getInt());
        System.out.println(b.getChar()+ ":" + b.getByte() + ","+ b.getDouble());

        System.out.println();

        System.out.println("b.setByte((byte) 99, a);");
        b.setByte((byte) 99, a);
        System.out.println(a.getString() + ":"+ a.getByte()+ "," + a.getInt());
        System.out.println(b.getChar() + ":"+ b.getByte() + ","+ b.getDouble());
        System.out.println();


        Base ba = new Base();
        ba.getmem(0);
        ba.getmem(1);
        ba.getmem(2);

        //输出类成员内容
        //此函数还需要整合，请以注释行标注嵌入的位置。
    }
}
