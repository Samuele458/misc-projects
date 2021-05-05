/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Calculator;

import javax.swing.*;
import java.awt.event.*;

/**
 *
 * @author samue
 */
public class CalculatorHandler implements ActionListener  {
    private JTextField outputField;
    private JButton[] buttons;
    
    private double partial;
    private String currentOp;
    private boolean opPressed;
    
    public CalculatorHandler( JTextField outputField, JButton[] buttons ) {
        this.outputField = outputField;
        this.buttons = buttons;
        
        clear();
    }
    
    @Override
    public void actionPerformed(ActionEvent e) {
        JButton buttonPressed = null;
        
        for( int i = 0; i < buttons.length; i++ ) {
            if(e.getSource() == buttons[i]) {
                buttonPressed = buttons[i];
            }
        }
        
        if( buttonPressed != null ) {
            String buttonText = buttonPressed.getText();
            
            if( isNumber(buttonText) ) {
                if( opPressed ) {
                    outputField.setText("0");
                    opPressed = false;
                }
                
                if( outputField.getText().equals("0") )
                    outputField.setText(buttonText);
                else outputField.setText(outputField.getText() + buttonText);
                
            } else if( isOperator(buttonText) ) {
                
                if( "".equals(currentOp) ) {
                    this.currentOp = buttonText;
                    this.partial = Double.parseDouble(outputField.getText());
                } else {
                    this.currentOp = buttonText;
                    this.partial = doOperation(this.partial, 
                                                this.currentOp,
                                                Double.parseDouble(outputField.getText()) );
                    outputField.setText(Double.toString(this.partial));
                }
                
                opPressed = true;
                
            } else if( buttonText.equals(".") && outputField.getText().indexOf(".") == -1 ) {
                
                outputField.setText(outputField.getText() + buttonText);
                
            } else  if( buttonText.equals("=") ) {
                this.partial = doOperation(this.partial, 
                                                this.currentOp,
                                                Double.parseDouble(outputField.getText()) );
                
                outputField.setText(Double.toString(this.partial));
                this.currentOp = "";
                this.opPressed = true;
            } else if( buttonText.equals("C") ) {
                clear();
            } else if( buttonText.equals(">") ) {
                if( !this.opPressed ) {
                    outputField.setText(outputField.getText().substring(0, outputField.getText().length() - 1) );
                }
            }
        }
    }
    
    public boolean isNumber(String str) {
        try {
            Integer.parseInt(str);
        } catch (NumberFormatException e) {
            return false;
        }
        return true;
    }
    
    public boolean isOperator(String str) {
      return "+".equals(str) || "-".equals(str) || "*".equals(str) || "/".equals(str);
    }
    
    public void clear() {
        this.partial = 0;
        this.outputField.setText("0");
        this.currentOp = "";
    }
    
    public double doOperation( double op1, String operator, double op2 ) {
        double result = 0;
        
        switch(operator) {
            case "+":
                result = op1 + op2;
                break;
                
            case "/":
                result = op1 / op2;
                break;
                
            case "*":
                result = op1 * op2;
                break;
                
            case "-":
                result = op1 - op2;
                break;
        }
        
        return result;
    }
}
