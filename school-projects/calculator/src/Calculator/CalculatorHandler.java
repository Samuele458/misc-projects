/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Calculator;

import javax.swing.*;
import java.awt.GridLayout;
import java.awt.BorderLayout;

import java.awt.*;
import java.awt.event.*;

/**
 *
 * @author samue
 */
public class CalculatorHandler implements ActionListener  {
    private JTextField outputField;
    private JButton[] buttons;
    
    private float tot;
    
    public CalculatorHandler( JTextField outputField, JButton[] buttons ) {
        this.outputField = outputField;
        this.buttons = buttons;
    }
    
    public void actionPerformed(ActionEvent e) {
        JButton buttonPressed = null;
        
        for( int i = 0; i < buttons.length; i++ ) {
            if(e.getSource() == buttons[i]) {
                buttonPressed = buttons[i];
            }
        }
        
        if( buttonPressed != null ) {
            outputField.setText(buttonPressed.getText());
        }
    }
}
