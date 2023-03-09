import pandas as pd

pd.set_option('display.max_columns', None)

nuclei_data = pd.read_csv('nuclear_data.csv')

# Table for small nuclei
small_nuclei_data = nuclei_data[['A', 'Z', 'mass']]
small_nuclei_data = small_nuclei_data[small_nuclei_data['A'] <= 20]
small_nuclei_data.to_csv('small_nuclei_data.csv')
