import source.Base;

public class B extends Base {
    protected int anInt;

    public B() {
        super();
        this.anInt = super.ran();
    }

    public int getAnInt() {
        return this.anInt;
    }

    public void setAnInt(int anInt) {
        this.anInt = anInt;
    }

    public void showallclassname() {
        super.showallclassname(this);
    }

    public void showfunname() {
        super.showfunname(this);
    }
}
