package LambdaExpression;

import java.time.LocalDate;
import java.util.ArrayList;
import java.util.List;
import java.util.Random;

/**
 * Created by shharn2 on 2017-01-06.
 */
public class Person {
    public enum Sex{
        MALE, FEMALE
    }

    String name;
    LocalDate birthday;
    Sex gender;
    String emailAddress;

    static public List<Person> createRoster(){
        List<Person> persons = new ArrayList<Person>();
        Person person = null;
        Random random = new Random(500);
        String emailBase = "@gmail.com";
        String idBase = "shharn";
        for(int i=0; i<30; i++) {
            person = new Person();
            person.name = "Han seunghwan" + i;
            person.birthday = LocalDate.of(random.nextInt(21) + 1985,
                    random.nextInt(11) +1,
                    random.nextInt(30) + 1);
            person.gender = random.nextBoolean() ? Sex.FEMALE : Sex.MALE;
            person.emailAddress = idBase + i + emailBase;
            persons.add(person);
        }
        return persons;
    }

    public int getAge(){
        return LocalDate.now().getYear() - birthday.getYear();
    }

    public void printPerson(){
        System.out.println("Name :\t\t" + name);
        System.out.println("Birth :\t\t " + birthday);
        System.out.println("Sex :\t\t" + gender);
        System.out.println("Email :\t\t" + emailAddress);
    }

    public Sex getGender(){
        return gender;
    }

    public String getEmailAddress(){
        return emailAddress;
    }
}
