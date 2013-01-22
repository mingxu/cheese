package com.cheese.generator;

import java.io.IOException;
import java.lang.reflect.Field;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;

/**
 * Created with IntelliJ IDEA.
 * User: ming
 * Date: 12/18/12
 * Time: 9:06 PM
 * To change this template use File | Settings | File Templates.
 */
public class Main {
    public static void main(String[] args) throws Exception {
//        if (args.length != 6)
//        {
//            System.out.println("Usage: <template folder> <template file> <generated folder> <generated file> <compiled folder> <classname>");
//        }
//
//        Main main = new Main();
//        main.execute(args[0], args[1], args[2], args[3], args[4], args[5]);

       for (MyTest value : MyTest.config) {
            Class<?> c = value.getDeclaringClass();
            Field f = c.getDeclaredField(value.name());
            MyAttribute a = f.getAnnotation(MyAttribute.class);
            String t = a.value();
            System.out.println(t);
        }
    }

    public void execute(String tempFolder, String tempFile, String genFolder, String genFile, String compFolder, String className) throws Exception {
        Generator generator = new Generator(tempFolder, genFolder);
        generator.getContext().put("compiledFolder", compFolder);
        generator.getContext().put("engine", this);
        generator.merge(tempFile, genFile);
        CompilerHelper compilerHelper = new CompilerHelper(compFolder);
        compilerHelper.compileClass(genFolder + "/" + genFile);
        Class<?> clazz = compilerHelper.getClass(className);
        Method method = clazz.getDeclaredMethod("execute");
        Object object = clazz.newInstance();
        System.out.println("Executing execute from class: " + className);
        method.invoke(object, null);
    }
}
