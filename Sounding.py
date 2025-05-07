import pandas as pd
import matplotlib.pyplot as plt

# Load the dataset
file_path = 'C:/Users/broan/Downloads/PASCAL Flight 3-28-25 - PASCAL Flight 3-28-25.csv'
df = pd.read_csv(file_path)

df.columns = df.columns.str.strip()

# Print column names to check what they are called 
print("Column Names:", df.columns.tolist())

# Convert all data to numeric values instead of float (I got so many errors), coercing errors to NaN
df['GPS Latitude'] = pd.to_numeric(df['GPS Latitude'], errors='coerce')
df['GPS Longitude'] = pd.to_numeric(df['GPS Longitude'], errors='coerce')
df['KM Alt'] = pd.to_numeric(df['KM Alt'], errors='coerce')
df['Payload State'] = pd.to_numeric(df['Payload State'], errors='coerce')

# Print data summar
print("Data Summary Before Filtering:")
print(df[['GPS Latitude', 'GPS Longitude', 'KM Alt']].describe())

# Remove NaN values
df = df.dropna()


# Print data summary after filtering out NAN
print("Data Summary After Filtering:")
print(df[['GPS Latitude', 'GPS Longitude', 'KM Alt']].describe())

# Extract relevant data
if {'GPS Latitude', 'GPS Longitude', 'KM Alt', 'Payload State'}.issubset(df.columns):
    latitude = df['GPS Latitude']
    longitude = df['GPS Longitude']
    altitude = df['KM Alt']
    payload = df['Payload State']
else:
    raise KeyError("One or more required columns are missing in the dataset.")

# Create a 3D plot
fig = plt.figure(figsize=(12, 8))
ax = fig.add_subplot(111, projection='3d')

# Scatter plot with color mapping to temperature
sc = ax.scatter(latitude, longitude, altitude, c=payload, cmap='twilight', marker='o')
plt.colorbar(sc, label='Payload State')

ax.set_xlim(34.5, 35)
ax.set_ylim(-86.8, -84.5)
ax.set_zlim(0, 30)
   
# Labels
ax.set_xlabel('Latitude')
ax.set_ylabel('Longitude')
ax.set_zlabel('Altitude (km)')
ax.set_title('3D Payload States')
plt.show()

































import pandas as pd
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

# Load the first dataset (File 1)
file_path1 = 'C:/Users/broan/Downloads/2023_08_02_20Z_searey.txt'
df1 = pd.read_csv(file_path1)

# Load the second dataset (File 2)
file_path2 = 'C:/Users/broan/Downloads/DC8 20-final - Sheet1 (1).csv'
df2 = pd.read_csv(file_path2)

# Rename columns to make them consistent for merging
df1.rename(columns={'latitude': 'Latitude', 'longitude': 'Longitude', 'altitude': 'Altitude', 'no2': 'NO2'}, inplace=True)
df2.rename(columns={'G_ALT': 'Altitude', 'NO2_ACES': 'NO2'}, inplace=True)

# Merge the two dataframes (assuming they have similar columns: 'Latitude', 'Longitude', 'Altitude', 'NO2')
df = pd.concat([df1[['Latitude', 'Longitude', 'Altitude', 'NO2']], df2[['Latitude', 'Longitude', 'Altitude', 'NO2']]], ignore_index=True)

# Create the 3D plot
fig = plt.figure(figsize=(10, 7))
ax = fig.add_subplot(111, projection='3d')

# Scatter plot: longitude, latitude, and altitude (with color representing NO₂ concentration)
sc = ax.scatter(df['Longitude'], df['Latitude'], df['Altitude'], c=df['NO2'], cmap='rainbow', s=15)

# Add color bar for NO₂ concentration
fig.colorbar(sc, label='NO₂ Concentration (ppb)')

# Set labels for axes
ax.set_xlabel('Longitude')
ax.set_ylabel('Latitude')
ax.set_zlabel('Altitude (m)')

ax.set_zlim(0, 1200)

# Title of the plot
ax.set_title('3D NO₂ Concentration Plot')

# Show the plot
plt.show()
