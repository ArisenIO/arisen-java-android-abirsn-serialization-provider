package one.block.testarisenjavaabirix;

import androidx.appcompat.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.TextView;

import one.block.arisenjava.error.serializationProvider.SerializationProviderError;
import one.block.arisenjavaabirixserializationprovider.AbiRixSerializationProviderImpl;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // Example of a call to a native method
        TextView tv = findViewById(R.id.sample_text);
        String results = "Waiting for AbiRixSerializationProviderImpl";
        try {
            AbiRixSerializationProviderImpl abiRixSerializationProviderImpl = new AbiRixSerializationProviderImpl();
            String contractStrOrig = "arisen.assert";
            long name64 = abiRixSerializationProviderImpl.stringToName64(contractStrOrig);
            String testStr = abiRixSerializationProviderImpl.name64ToString(name64);

            results = String
                    .format("Original: %s\nname64: %d\ntest: %s", contractStrOrig, name64, testStr);
            tv.setText(results);
        } catch (SerializationProviderError serializationProviderError) {
            results = "Error from SerializationProvider: " + serializationProviderError.getLocalizedMessage();
        }
        tv.setText(results);
    }

}
