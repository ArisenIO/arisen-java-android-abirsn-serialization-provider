package one.block.arisenjavaabirixserializationprovider;

import one.block.arisenjava.error.serializationProvider.SerializationProviderError;
import org.jetbrains.annotations.NotNull;

/**
 * Error class is used when there is an exception when the ABIRIX c++ code attempts to create its
 * working context during initialization.
 */

public class AbirixContextNullError extends SerializationProviderError {

    public AbirixContextNullError() {
    }

    public AbirixContextNullError(@NotNull String message) {
        super(message);
    }

    public AbirixContextNullError(@NotNull String message,
            @NotNull Exception exception) {
        super(message, exception);
    }

    public AbirixContextNullError(@NotNull Exception exception) {
        super(exception);
    }
}
