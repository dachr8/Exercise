package B;

import A.A;

public class B {
    private byte aByte;
    private double aDouble;
    private char aChar;

    public B() {
        aByte = 0;
        aDouble = -1.0D;
        aChar = '\0';
    }

    public B(byte aByte, double aDouble, char aChar) {
        this.aByte = aByte;
        this.aDouble = aDouble;
        this.aChar = aChar;
    }

    //byte
    public byte getByte() {
        return aByte;
    }

    public void setByte(byte aByte) {
        this.aByte = aByte;
    }

    public void setByte(byte aByte, A a) {
        this.aByte = aByte;
        a.setByte(aByte);
    }

    //double
    public double getDouble() {
        return aDouble;
    }

    public void setDouble(double aDouble) {
        this.aDouble = aDouble;
    }

    //char
    public char getChar() {
        return aChar;
    }

    public void setChar(char aChar) {
        this.aChar = aChar;
    }

}
