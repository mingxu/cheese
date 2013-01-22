package com.cheese.generator;

import org.apache.velocity.Template;
import org.apache.velocity.VelocityContext;
import org.apache.velocity.app.VelocityEngine;
import org.apache.velocity.context.Context;

import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.io.Writer;

/**
 * Created with IntelliJ IDEA.
 * User: ming
 * Date: 12/14/12
 * Time: 8:15 PM
 * To change this template use File | Settings | File Templates.
 */
public class Generator {
    private Context context;
    private VelocityEngine engine;
    private String targetFolder;

    public Generator(String templateFolder, String targetFolder) {
        engine = new VelocityEngine();
        engine.setProperty("file.resource.loader.path", templateFolder);
        engine.init();
        context = new VelocityContext();
        this.targetFolder = targetFolder;
        context.put("templateFolder", templateFolder);
        context.put("targetFolder", targetFolder);
    }

    public Context getContext() {
        return context;
    }

    public void merge(String templateFile, String targetFile) throws IOException {
        Template template = engine.getTemplate(templateFile);
        FileWriter writer = new FileWriter(targetFolder + "/" + targetFile);
        template.merge(this.context, writer );
        writer.close();
        System.out.println("generated file:" + targetFile);
    }
}
