
package Calculator;

import javax.swing.*;
import java.awt.GridLayout;
import java.awt.BorderLayout;
import java.awt.Dimension;
import java.awt.Font;

/**
 *
 * @author Samuele Girgenti
 */
public class CalculatorFrame extends JFrame {
    
    public static final String[] BUTTONS = {
        ">", "C", "/", "*",
        "7", "8", "9", "+",
        "4", "5", "6", "-",
        "1", "2", "3", "C",
        "0", ".", "+/-", "="
    };
    
    private JTextField outputField;
    private JButton[] buttons;
    
    CalculatorFrame() {
        
        Font font = new Font(Font.SANS_SERIF, Font.BOLD, 24);
        
        //calculator output field
        outputField = new JTextField(9);
        outputField.setHorizontalAlignment(SwingConstants.RIGHT);
        outputField.setMaximumSize(new Dimension(Integer.MAX_VALUE, outputField.getMinimumSize().height + 3000));
        outputField.setFont( font );
        
        JPanel buttonsPanel = new JPanel( new GridLayout(0,4));
        
        buttons = new JButton[BUTTONS.length];
        
        CalculatorHandler handler = new CalculatorHandler( outputField, buttons );
        
        for( int i = 0; i < BUTTONS.length; i++ ) {
            JButton currentButton = new JButton(BUTTONS[i]);
            buttonsPanel.add( currentButton );
            buttons[i] = currentButton;
            buttons[i].setFont( font );
            buttons[i].addActionListener( handler );            
        }
        /*
        JPanel framePanel = new JPanel( new BorderLayout() );
        framePanel.add(outputField, BorderLayout.PAGE_START);
        framePanel.add(buttonsPanel, BorderLayout.CENTER);*/
        
        getContentPane().setLayout(
            new BoxLayout(getContentPane(), BoxLayout.PAGE_AXIS)
        );
        this.add( outputField );
        this.add(buttonsPanel);
        //this.getContentPane().add(framePanel);
        this.pack();
        this.setDefaultCloseOperation( JFrame.EXIT_ON_CLOSE );
        this.setSize(600,400);
        this.setVisible(true);
    }
}
