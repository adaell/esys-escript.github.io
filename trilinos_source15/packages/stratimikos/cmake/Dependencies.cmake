# Note that Belos and ML do *not* have
# a required dependence on Epetra but the Stratimikos Belos and ML adapters
# need the Thyra/Epetra adapters.
TRIBITS_PACKAGE_DEFINE_DEPENDENCIES(
  LIB_REQUIRED_PACKAGES ThyraCore
  LIB_OPTIONAL_PACKAGES Amesos Amesos2 AztecOO Belos Ifpack Ifpack2 ML EpetraExt ThyraEpetraAdapters ThyraTpetraAdapters
  TEST_OPTIONAL_PACKAGES Triutils Ifpack2 Galeri ThyraEpetraAdapters ThyraTpetraAdapters
  )
# Note: EpetraExt is used by the AztecOO adapters
