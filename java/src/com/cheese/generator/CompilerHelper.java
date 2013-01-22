package com.cheese.generator;

import javax.tools.JavaCompiler;
import javax.tools.JavaFileObject;
import javax.tools.StandardJavaFileManager;
import javax.tools.ToolProvider;
import java.io.File;
import java.io.IOException;
import java.net.MalformedURLException;
import java.net.URL;
import java.net.URLClassLoader;
import java.util.Arrays;

/**
 * Created with IntelliJ IDEA.
 * User: ming
 * Date: 12/18/12
 * Time: 8:47 PM
 * To change this template use File | Settings | File Templates.
 */
public class CompilerHelper {
    private JavaCompiler compiler = ToolProvider.getSystemJavaCompiler();
    private StandardJavaFileManager fileManager;
    private String[] options;
    private String targetFolder;

    public CompilerHelper(String targetFolder) {
        options = new String[]{"-d", targetFolder};
        this.targetFolder = targetFolder;
    }

    public boolean compileClass(String file) throws IOException {
        fileManager = compiler.getStandardFileManager(null,null,null);
        Iterable<? extends JavaFileObject> fileObjects = fileManager.getJavaFileObjects(new File(file));
        boolean  result = compiler.getTask(null, null, null, Arrays.asList(options), null, fileObjects).call();
        fileManager.close();
        System.out.println("Compiling " + file + " " + (result ? " succeeded!" : "failed!"));
        return result;
    }

    public Class<?> getClass(String classFullName) throws MalformedURLException, ClassNotFoundException {
        URLClassLoader loader = new URLClassLoader(new URL[]{new URL("file://" + this.targetFolder)});
        return loader.loadClass(classFullName);
    }

}
