package A;

import B.B;

public class A {

    private byte aByte;
    private int anInt;
    private String aString;

    public A() {
        aByte = 0;
        anInt = 0X50505050;
        aString = null;
    }

    public A(byte aByte, int anInt, String aString) {
        this.aByte = aByte;
        this.anInt = anInt;
        this.aString = aString;
    }

    //byte
    public byte getByte() {
        return aByte;
    }

    public void setByte(byte aByte) {
        this.aByte = aByte;
    }

    public void setByte(byte aByte, B b) {
        this.aByte = aByte;
        b.setByte(aByte);
    }

    //int
    public int getInt() {
        return anInt;
    }

    public void setInt(int anInt) {
        this.anInt = anInt;
    }

    //string
    public String getString() {
        return aString;
    }

    public void setString(String anString) {
        this.aString = anString;
    }


}
