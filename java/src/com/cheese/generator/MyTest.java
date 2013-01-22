package com.cheese.generator;

/**
 * Created with IntelliJ IDEA.
 * User: ming
 * Date: 12/21/12
 * Time: 8:27 PM
 * To change this template use File | Settings | File Templates.
 */
public enum MyTest {
    @MyAttribute("hello world!")
    MyTest1,

    @MyAttribute("byte")
    MyTest2;


    @Config
    public static final MyTest[] config = new MyTest[]{MyTest1, MyTest2};
}
