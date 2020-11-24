package labs.peeps.arisenjavaABIRSNserializationprovider;

import labs.peeps.arisenjava.error.serializationProvider.SerializationProviderError;
import org.jetbrains.annotations.NotNull;

/**
 * Error class is used when there is an exception when the ABIRSN c++ code attempts to create its
 * working context during initialization.
 */

public class ABIRSNContextNullError extends SerializationProviderError {

    public ABIRSNContextNullError() {
    }

    public ABIRSNContextNullError(@NotNull String message) {
        super(message);
    }

    public ABIRSNContextNullError(@NotNull String message,
            @NotNull Exception exception) {
        super(message, exception);
    }

    public ABIRSNContextNullError(@NotNull Exception exception) {
        super(exception);
    }
}
