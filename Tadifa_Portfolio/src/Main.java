    import javax.swing.*;
    import java.awt.*;
    import java.awt.event.*;

    public class Main {
        public static void main(String[] args) {
            try {
                UIManager.setLookAndFeel("javax.swing.plaf.nimbus.NimbusLookAndFeel");
            } catch (Exception ignored) {}

            JFrame frame = new JFrame(" Simple Calculator ");
            frame.getContentPane().setBackground(new Color(240, 248, 255));

            JTextField textField = new JTextField();
            textField.setFont(new Font("Comic Sans MS", Font.BOLD, 24));
            textField.setHorizontalAlignment(JTextField.RIGHT);
            textField.setBackground(new Color(255, 255, 204));
            textField.setEditable(false);

            JPanel panel = new JPanel(new GridLayout(5, 4, 8, 8));
            panel.setBackground(new Color(224, 255, 255));
            String[] buttons = {
                "7", "8", "9", "/",
                "4", "5", "6", "*",
                "1", "2", "3", "-",
                "0", "C", "=", "+",
                "^", "√", "%", "!"
            };

            for (String text : buttons) {
                JButton btn = new JButton(text);
                btn.setFont(new Font("Comic Sans MS", Font.BOLD, 20));
                btn.setFocusPainted(false);
                btn.setBackground(new Color(255, 228, 225));
                btn.setForeground(new Color(70, 70, 70));
                btn.setBorder(BorderFactory.createLineBorder(new Color(135, 206, 250), 2));
                // Color special buttons
                if ("C".equals(text)) btn.setBackground(new Color(255, 182, 193));
                if ("=".equals(text)) btn.setBackground(new Color(144, 238, 144));
                if ("^√%!".contains(text)) btn.setBackground(new Color(255, 218, 185));
                panel.add(btn);
            }

            frame.setLayout(new BorderLayout(10, 10));
            frame.add(textField, BorderLayout.NORTH);
            frame.add(panel, BorderLayout.CENTER);
            frame.setSize(350, 480);
            frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
            frame.setLocationRelativeTo(null);
            frame.setVisible(true);


            final String[] operator = {""};
            final double[] num1 = {0};
            final boolean[] start = {true};

            for (Component comp : panel.getComponents()) {
                if (comp instanceof JButton) {
                    JButton btn = (JButton) comp;
                    btn.addActionListener(e -> {
                        String cmd = btn.getText();
                        if ("0123456789".contains(cmd)) {
                            if (start[0]) {
                                textField.setText(cmd);
                                start[0] = false;
                            } else {
                                textField.setText(textField.getText() + cmd);
                            }
                        } else if ("+-*/^%".contains(cmd)) {
                            operator[0] = cmd;
                            num1[0] = Double.parseDouble(textField.getText());
                            start[0] = true;
                        } else if ("√".equals(cmd)) {
                            try {
                                double value = Double.parseDouble(textField.getText());
                                textField.setText("√" + value + " = " + Math.sqrt(value));
                            } catch (Exception ex) {
                                textField.setText("Error");
                            }
                            start[0] = true;
                        } else if ("!".equals(cmd)) {
                            try {
                                int value = Integer.parseInt(textField.getText());
                                textField.setText(value + "! = " + factorial(value));
                            } catch (Exception ex) {
                                textField.setText("Error");
                            }
                            start[0] = true;
                        } else if ("=".equals(cmd)) {
                            try {
                                double num2 = Double.parseDouble(textField.getText());
                                double result = 0;
                                switch (operator[0]) {
                                    case "+": result = num1[0] + num2; break;
                                    case "-": result = num1[0] - num2; break;
                                    case "*": result = num1[0] * num2; break;
                                    case "/": result = num2 != 0 ? num1[0] / num2 : Double.NaN; break;
                                    case "^": result = Math.pow(num1[0], num2); break;
                                    case "%": result = num2 != 0 ? num1[0] % num2 : Double.NaN; break;
                                }
                                textField.setText(num1[0] + " " + operator[0] + " " + num2 + " = " + result);
                            } catch (Exception ex) {
                                textField.setText("Error");
                            }
                            start[0] = true;
                        } else if ("C".equals(cmd)) {
                            textField.setText("");
                            operator[0] = "";
                            num1[0] = 0;
                            start[0] = true;
                        }
                    });
                }
            }
        }

        private static long factorial(int n) {
            if (n < 0) return 0;
            long fact = 1;
            for (int i = 2; i <= n; i++) {
                fact *= i;
            }
            return fact;
        }
    } 