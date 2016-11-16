package com.github.sandeepmistry.arduino.nRF5;

import cc.arduino.packages.Uploader;
import cc.arduino.packages.uploaders.SerialUploader;

import java.awt.Dimension;

import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.InputStream;
import java.io.File;

import java.lang.Runnable;
import java.lang.Thread;

import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

import java.net.URL;

import javax.swing.JOptionPane;
import javax.swing.JScrollPane;
import javax.swing.JTextArea;

import java.util.HashMap;
import java.util.Map;
import java.util.zip.ZipInputStream;
import java.util.zip.ZipEntry;

import processing.app.Editor;
import processing.app.PreferencesData;
import processing.app.tools.Tool;

public class nRF5FlashSoftDevice implements Tool {
  private Map<String, String> urls = new HashMap<String, String>();
  private Editor editor;

  public void init(Editor editor) {
    urls.put("s110", "http://www.nordicsemi.com/eng/content/download/80234/1351257/file/s110_nrf51_8.0.0.zip");
    urls.put("s130", "http://www.nordicsemi.com/eng/content/download/95150/1606929/file/s130_nrf51_2.0.0.zip");
    urls.put("s132", "http://www.nordicsemi.com/eng/content/download/95151/1606944/file/s132_nrf52_2.0.0.zip");

    this.editor = editor;
  }

  public String getMenuTitle() {
    return "nRF5 Flash SoftDevice";
  }

  public void run() {
    if (!PreferencesData.get("target_platform").equals("nRF5")) {
      editor.statusError(getMenuTitle() + " is only supported on 'Nordic Semiconductor nRF5 Boards' boards!");
      return;
    }

    String softDevice = PreferencesData.get("custom_softdevice");
    if (softDevice == null || softDevice.endsWith("none")) {
      editor.statusError("No SoftDevice selected!");
      return;
    }

    String programmer = PreferencesData.get("programmer");
    if (programmer == null || !programmer.startsWith("sandeepmistry:")) {
      editor.statusError("Unsupported programmer!");
      return;
    }

    softDevice = softDevice.substring(softDevice.lastIndexOf("_") + 1);
    String url = urls.get(softDevice);

    if (url == null) {
      editor.statusError("Unsupported SoftDevice!");
      return;
    }

    Path softdevicePath = Paths.get(PreferencesData.get("runtime.platform.path"), "cores", "nRF5", "SDK", "components", "softdevice", softDevice, "hex");

    Runnable runnable = () -> {
      try {
        if (Files.list(softdevicePath).count() < 3) {
          System.out.println("Downloading '" +url + "' ...");

          InputStream is = new URL(url).openStream();
          ByteArrayOutputStream outputStream = new ByteArrayOutputStream();

          byte[] chunk = new byte[32 * 1024];
          int bytesRead;

          while ((bytesRead = is.read(chunk)) > 0) {
            System.out.print(".");
            outputStream.write(chunk, 0, bytesRead);
          }

          System.out.println("done");

          ZipInputStream zis = new ZipInputStream(new ByteArrayInputStream(outputStream.toByteArray()));
          ZipEntry entry;

          String licenseAgreementFilename = "";
          StringBuilder licenseAgreementBuilder = new StringBuilder();

          String softdeviceFilename = "";
          StringBuilder softdeviceBuilder = new StringBuilder();

          while ((entry = zis.getNextEntry()) != null) {
            if (entry.getName().endsWith("agreement.txt")) {
              licenseAgreementFilename = entry.getName();

              for (int i = 0; i < entry.getSize(); i++) {
                licenseAgreementBuilder.append((char)zis.read());
              }
            } else if (entry.getName().endsWith("softdevice.hex")) {
              softdeviceFilename = entry.getName();

              for (int i = 0; i < entry.getSize(); i++) {
                softdeviceBuilder.append((char)zis.read());
              }
            }
          }

          JTextArea textArea = new JTextArea(licenseAgreementBuilder.toString());
          textArea.setColumns(80);
          textArea.setRows(50);
          textArea.setLineWrap(true);
          textArea.setWrapStyleWord(true);
          textArea.setSize(textArea.getPreferredSize().width, 1);

          JScrollPane scrollPane = new JScrollPane(textArea);
          scrollPane.setPreferredSize( new Dimension(textArea.getPreferredSize().width, 500 ) );

          int result = JOptionPane.showOptionDialog(null, scrollPane, "NORDIC SEMICONDUCTOR ASA SOFTDEVICE LICENSE AGREEMENT", JOptionPane.DEFAULT_OPTION, JOptionPane.QUESTION_MESSAGE, null, new Object[]{"Accept", "Decline"}, "Decline");

          if (result != 0) {
            return;
          }

          Files.write(Paths.get(softdevicePath.toString(), licenseAgreementFilename  ), String.valueOf(licenseAgreementBuilder).getBytes());
          Files.write(Paths.get(softdevicePath.toString(), softdeviceFilename), String.valueOf(softdeviceBuilder).getBytes());
        }

        Uploader uploader = new SerialUploader();
        if (uploader.burnBootloader()) {
          editor.statusNotice("Done flashing SoftDevice.");
        } else {
          editor.statusError("Error while flashing SoftDevice.");
        }
      } catch (Exception e) {
        editor.statusError("Error while flashing SoftDevice.");
        System.err.println(e);
        return;
      }
    };

    Thread thread = new Thread(runnable);
    thread.start();
  }
}
